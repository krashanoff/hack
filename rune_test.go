package main

import "testing"

func Assert(i ...interface{}) bool {
	prev := i[0]

	for _, e := range i {
		if e != prev {
			return false
		}
		prev = e
	}

	return true
}

func TestTrie(t *testing.T) {
	root := NewTrie()

	insertLog := func(s string) {
		root.Insert(s)
		t.Log(root)
	}

	insertLog("*.com")
	insertLog("*.net")
	insertLog("mm")

	root.RunFunc(func(tr *Trie) {
		t.Logf("%c", tr.Val())
	})

	if !root.Contains("cars.com") {
		t.Fatalf("???????")
	}
}
