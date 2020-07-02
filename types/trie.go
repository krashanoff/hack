package types

// SimpleTree is a super simple
// thread-safe tree.
type SimpleTree struct {
	val      byte
	terminal chan bool
	children []*SimpleTree
}

// NewSimpleTree creates a tree.
func NewSimpleTree() *SimpleTree {
	return &SimpleTree{0, make(chan bool, 1), make([]*SimpleTree, 0)}
}

// Get the value of the node.
func (t *SimpleTree) Get() byte {
	ter := <-t.terminal
	v := t.val
	t.terminal <- ter
	return v
}

// Insert a value into the tree.
func (t *SimpleTree) Insert(b []byte) {
	terminal := <-t.terminal

	if t.val == b[0] {
		t.terminal <- terminal
		t.Insert(b[1:])
	}

	for _, c := range t.children {
		cTerm := <-c.terminal

		if c.val == b[0] {
			c.Insert(b)
		}

		c.terminal <- cTerm
	}
}

// Contains confirms the presence of a value in the tree.
func (t *SimpleTree) Contains(b []byte) bool {
	return false
}
