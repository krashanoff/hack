package types

/**
 * runetrie.go
 *
 * An experiment conducted while contributing to
 * k6.
 */

// Trie of runes with support for wildcards at the start
// of any inserted string.
type Trie struct {
	r        rune
	children []*Trie
	terminal bool
}

// NewTrie creation.
func NewTrie(terminal bool, r rune) *Trie {
	return &Trie{r, make([]*Trie, 0), terminal}
}

// Insert a string into the Trie.
func (t *Trie) Insert(s []rune) {
	if len(s) == 0 {
		return
	}

	// in children?
	for _, c := range t.children {
		if c.r == s[len(s)-1] {
			c.Insert(s[:len(s)-1])
			return
		}
	}

	// create the required child if not found.
	n := NewTrie(len(s) == 1, s[len(s)-1])
	t.children = append(t.children, n)
	n.Insert(s[:len(s)-1])
}

// Contains a string?
func (t *Trie) Contains(s []rune) bool {
	if len(s) == 0 {
		return false
	}

	char := s[len(s)-1]
	use := s[:len(s)-1]
	if t.r == 0 {
		use = s
		char = 0
	}

	switch {
	case t.r == '*':
		return true
	case t.r != char:
		return false
	case len(s) == 1:
		return t.r == char && t.terminal

	default:
		for _, c := range t.children {
			if c.Contains(use) {
				return true
			}
		}
	}

	return false
}

// RunFunc on every node
func (t *Trie) RunFunc(f func(*Trie)) {
	// run on current
	f(t)

	// run on children
	for _, c := range t.children {
		c.RunFunc(f)
	}
}
