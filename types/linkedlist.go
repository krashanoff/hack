package types

// LinkedList is a thread-safe, hand-over-hand locking,
// doubly-linked list with a dummy head.
type LinkedList struct {
	val  byte
	prev chan *LinkedList
	next chan *LinkedList
}

// Next item
func (l *LinkedList) Next() {
	// release current list
}

// Insert a byte to the list.
func (l *LinkedList) Insert(b byte) {
}
