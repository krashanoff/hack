package types

/**
 * runetrie.go
 *
 * An experiment conducted while contributing to
 * k6.
 *
 * A tree with a dummy head node that stores runes
 * from a string in reverse order.
 */

// Trie of hostnames with support for wildcards at
// the start of each hostname.
type Trie struct {
	r        rune
	children []*Trie
	terminal bool // end of valid match?
}

// NewTrie returns a valid head for a Trie.
func NewTrie() *Trie {
	return &Trie{-1, make([]*Trie, 0), false}
}

// Insert a string into the Trie.
func (t *Trie) Insert(s []rune) {
	if s == nil || len(s) == 0 {
		return
	}

	// in children?
	lastIdx := len(s) - 1
	for _, c := range t.children {
		if c.r == s[lastIdx] {
			c.Insert(s[:lastIdx])
			return
		}
	}

	// if not, create the child.
	n := &Trie{s[lastIdx], make([]*Trie, 0), len(s) == 1}
	t.children = append(t.children, n)
	n.Insert(s[:lastIdx])
}

// Contains returns whether a given string has been inserted into the Trie.
func (t *Trie) Contains(s []rune) bool {
	if s == nil || len(s) == 0 {
		return false
	}

	lastRune := s[len(s)-1]    // by default, the last rune.
	insertNext := s[:len(s)-1] // by default, the string to pass down is sans last rune.

	// the root node requires that we iterate over
	// its children and the entire string.
	if t.r == -1 {
		insertNext = s
		lastRune = -1
	}

	switch {
	case t.r == '*': // wildcards validate all strings
		return true
	case t.r != lastRune: // if no match, return false
		return false
	case len(s) == 1: // if of length one, there should be a match and a terminal
		return t.r == lastRune && t.terminal
	default: // otherwise, iterate over children
		for _, c := range t.children {
			if c.Contains(insertNext) {
				return true
			}
		}
	}

	return false
}

// RunFunc f on every node in a Trie.
func (t *Trie) RunFunc(f func(*Trie)) {
	// run on current
	f(t)

	// run on children
	for _, c := range t.children {
		c.RunFunc(f)
	}
}
