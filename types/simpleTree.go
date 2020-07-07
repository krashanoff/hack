package types

// SimpleTree is a super simple
// thread-safe insertion tree.
type SimpleTree struct {
	val      byte
	root     chan bool // root indicator that doubles as a lock
	children []*SimpleTree
}

// NewSimpleTree creates a tree.
func NewSimpleTree(initialVals ...byte) *SimpleTree {
	t := newNode(0, true)
	t.Insert(initialVals)
	return t
}

// used to make a node
func newNode(val byte, root bool) *SimpleTree {
	t := &SimpleTree{val, make(chan bool, 1), make([]*SimpleTree, 0)}
	t.root <- root
	return t
}

// Insert a value into the tree.
func (t *SimpleTree) Insert(b []byte) {
	if len(b) == 0 {
		return
	}

	ter := <-t.root // acquire the lock for the node

	for _, c := range t.children {
		if c.val == b[0] {
			t.root <- ter
			c.Insert(b[1:])
			return
		}
	}

	// otherwise, create new node
	n := newNode(b[0], false)
	t.children = append(t.children, n)
	t.root <- ter
	n.Insert(b[1:])
}

// Contains confirms the presence of a value in the tree.
func (t *SimpleTree) Contains(b []byte) bool {
	if len(b) == 0 {
		return true
	}

	ter := <-t.root

	for _, c := range t.children {
		if c.val == b[0] {
			t.root <- ter
			return c.Contains(b[1:])
		}
	}

	t.root <- ter
	return false
}
