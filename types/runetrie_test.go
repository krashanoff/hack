package types

import "testing"

func TestTrie(t *testing.T) {
	root := RuneTrie{}

	insertLog := func(s string) {
		root.Insert(s)
		t.Log(root)
	}
	containsLog := func(s string) (bool, string) {
		t.Logf("testing contain with %s", s)
		return root.Contains(s)
	}

	insertLog("*.com")
	insertLog("*.net")
	insertLog("mm")
	insertLog("*mmmm")
	insertLog("domain.name")

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
		"",
	}

	for _, s := range shouldContain {
		if c, _ := containsLog(s); !c {
			t.Fatalf("%s not present\n", s)
		}
	}
	for _, s := range shouldNotContain {
		if c, m := containsLog(s); c {
			t.Fatalf("%s was present. Matched (%s)\n", s, m)
		}
	}
}
