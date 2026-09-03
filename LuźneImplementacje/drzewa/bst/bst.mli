type key = int
type 'a bst = Leaf | Node of 'a bst * 'a * key * 'a bst
val find : 'a bst -> key -> 'a bst
val insert : 'a bst -> key -> 'a -> 'a bst
val findmin : 'a bst -> 'a bst
val delete : 'a bst -> key -> 'a bst
val leftRotate : 'a bst -> 'a bst
val rightRotate : 'a bst -> 'a bst
