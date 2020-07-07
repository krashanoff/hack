package types

import (
	"fmt"
	"math/rand"
	"testing"
	"time"

	"github.com/stretchr/testify/assert"
)

func TestSimpleTreeSingleThread(t *testing.T) {
	root := NewSimpleTree()
	assert.NotNil(t, root)

	t.Run("Insert", func(t *testing.T) {
		root := NewSimpleTree()
		assert.NotNil(t, root)
		val := []byte("some value")
		root.Insert(val)
		assert.NotNil(t, root.children)
		assert.NotEmpty(t, root.children)
	})
	t.Run("Contains", func(t *testing.T) {
		root := NewSimpleTree()
		assert.NotNil(t, root)
		val1 := []byte("myval1")
		val2 := []byte("myval2")
		root.Insert(val1)
		root.Insert(val2)
		assert.NotNil(t, root.children)
		assert.Equal(t, len(root.children), 1)
		assert.True(t, root.Contains(val1))
	})
}

func TestSimpleTreeMultiThread(t *testing.T) {
	t.Log("tests are of the form (strLen)x(threadCount)")

	nThreads := func(threadCount, strLen int) func(*testing.T) {
		if threadCount == 0 {
			threadCount = 1
		}
		if strLen == 0 {
			strLen = 1
		}

		return func(t *testing.T) {
			root := NewSimpleTree()
			assert.NotNil(t, root)

			inserted := make(chan []byte, threadCount)

			for i := 0; i < threadCount; i++ {
				go func(t *testing.T) {
					randomByteStr := make([]byte, 0)

					for i := 0; i < strLen; i++ {
						randomByteStr = append(randomByteStr, byte(rand.Intn(128)))
					}

					root.Insert(randomByteStr)
					inserted <- randomByteStr
				}(t)
			}

			for i := 0; i < threadCount; i++ {
				b := <-inserted
				t.Logf("Received random string %x", b)
				assert.True(t, root.Contains(b))
			}
		}
	}

	// test with 0-100 threads and 0-100 units of work in increments of 5.
	t.Run("VariableThread", func(t *testing.T) {
		for threadCount := 0; threadCount <= 100; threadCount += 5 {
			for strLen := 0; strLen <= 100; strLen += 5 {
				t.Run(fmt.Sprintf("%dx%d", threadCount, strLen), nThreads(threadCount, strLen))
			}
		}
	})

	// test with 1000 threads all independently verifying **at the same time**.
	t.Run("IntensiveThread", func(t *testing.T) {
		threadCount := 1000
		root := NewSimpleTree()
		done := make(chan bool, threadCount)

		for i := 0; i < threadCount; i++ {
			go func(done chan bool) {
				// pick a random amount of work
				workAmt := rand.Intn(threadCount)

				// insert something random
				randomByteStr := make([]byte, 0)
				for i := 0; i < workAmt; i++ {
					randomByteStr = append(randomByteStr, byte(rand.Intn(128)))
				}
				root.Insert(randomByteStr)

				// wait a bit to verify
				time.Sleep(10 * time.Millisecond)
				assert.True(t, root.Contains(randomByteStr))
				done <- true
			}(done)
		}

		// wait
		for i := 0; i < threadCount; i++ {
			<-done
		}
	})
}

func TestSimpleTreeIntensive(t *testing.T) {

}
