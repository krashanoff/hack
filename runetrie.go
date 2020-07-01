package main

// Trie of runes with support for wildcards at the start
// of any inserted string.
type Trie struct {
	r        rune
	children []*Trie
}

// NewTrie creation.
func NewTrie(r ...rune) *Trie {
	switch len(r) {
	case 0:
		return &Trie{0, make([]*Trie, 0)}
	case 1:
		return &Trie{r[0], make([]*Trie, 0)}
	default:
		return nil
	}
}

// Val of a node
func (t *Trie) Val() rune {
	return t.r
}

// Insert a string into the Trie.
func (t *Trie) Insert(s string) {
	if len(s) == 0 {
		return
	}

	rStr := []rune(s)
	char := rStr[len(rStr)-1]

	// in children?
	for _, c := range t.children {
		if c.r == char {
			c.Insert(string(rStr[:len(rStr)-1]))
			return
		}
	}

	// create the required child if not found.
	n := NewTrie(char)
	t.children = append(t.children, n)
	n.Insert(string(rStr[:len(rStr)-1]))
}

// Contains a string?
func (t *Trie) Contains(s string) bool {
	if t.r == 0 {
		for _, c := range t.children {
			if c.Contains(s) {
				return true
			}
		}

		return false
	}

	rStr := []rune(s)
	char := rStr[len(rStr)-1]

	if t.r == rune('*') {
		return true
	}

	if t.r != char {
		return false
	}

	if t.r == char {
		for _, c := range t.children {
			if c.Contains(string(rStr[:len(rStr)-1])) {
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
