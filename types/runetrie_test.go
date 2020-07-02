package types

import "testing"

func TestTrie(t *testing.T) {
	root := NewTrie(false, 0)

	insertLog := func(s string) {
		root.Insert([]rune(s))
		t.Log(root)
	}
	containsLog := func(s string) bool {
		t.Logf("testing contain with %s", s)
		return root.Contains([]rune(s))
	}

	insertLog("*.com")
	insertLog("*.net")
	insertLog("mm")
	insertLog("*mmmm")
	insertLog("domain.name")

	t.Log("traversing tree:")
	root.RunFunc(func(tr *Trie) {
		t.Logf("{ %c, %v, %v }", tr.r, tr.children, tr.terminal)
	})

	shouldContain := []string{
		"cars.com",
		"ss.ssssss.com",
		"c.net",
		"b.net",
		"mm",
		"ammmm",
		"aaaaaaaaammmm",
	}
	shouldNotContain := []string{
		"m",
		"mmm",
		"aaaaaaaaaaaaaaa",
		"car accident",
	}

	for _, s := range shouldContain {
		if !containsLog(s) {
			t.Fatalf("%s not present\n", s)
		}
	}
	for _, s := range shouldNotContain {
		if containsLog(s) {
			t.Fatalf("%s was present\n", s)
		}
	}
}
