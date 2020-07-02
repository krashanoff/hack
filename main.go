package main

import (
	"fmt"
	"regexp"
)

func main() {
	a, _ := regexp.MatchString("^\\*?(\\pL|[0-9\\.])*", "a*b")
	fmt.Println(a)
}
