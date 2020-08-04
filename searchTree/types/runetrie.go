package types

/**
 * runetrie.go
 *
 * An experiment conducted while contributing to
 * k6.
 *
 * A tree that stores runes from a string in reverse
 * order, with support for wildcards.
 */

// RuneTrie is a tree of runes. Wildcards are supported
// at the start of a string.
type RuneTrie struct {
	children []*RuneTrie
	r        rune
	terminal bool // end of a valid match
}

// Insert a string into the given RuneTrie.
func (t *RuneTrie) Insert(s string) {
	if len(s) == 0 {
		return
	}

	rStr := []rune(s)
	last := len(rStr) - 1
	for _, c := range t.children {
		if c.r == rStr[last] {
			c.Insert(string(rStr[:last]))
		}
	}

	n := &RuneTrie{nil, rStr[last], len(rStr) == 1}
	t.children = append(t.children, n)
	n.Insert(string(rStr[:last]))
}

// Contains returns whether s matches a pattern in the RuneTrie
// along with the matching pattern, if one was found.
func (t *RuneTrie) Contains(s string) (bool, string) {
	for _, c := range t.children {
		if b, m := c.childContains(s, ""); b {
			return b, m
		}
	}
	return false, ""
}

// recursively traverse RuneTrie children searching for a match.
func (t *RuneTrie) childContains(s string, match string) (bool, string) {
	if len(s) == 0 {
		return false, ""
	}

	rStr := []rune(s)
	last := len(rStr) - 1

	switch {
	case t.r == '*':
		return true, "*" + match
	case t.r != rStr[last]:
		return false, ""
	case len(s) == 1:
		return t.terminal, string(t.r) + match
	default:
		for _, c := range t.children {
			if b, m := c.childContains(string(rStr[:last]), string(t.r)+match); b {
				return b, m
			}
		}
	}

	return false, ""
}
