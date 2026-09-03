type key = int
type 'a bst = Leaf | Node of 'a bst * 'a * key * 'a bst

let rec find (t : 'a bst) (k : key) : 'a = 
    match t with
    | Leaf -> Printf.eprintf "key %i not found" k
    | Node(left, v, rootkey, right) ->
        if rootkey = k then 
            v
        else if k > rootkey 
            then find right k
        else
            find left k

let rec insert (t : 'a bst) (k : key) (v : 'a) = 
    match t with
    | Leaf -> Node(Leaf, v, k, Leaf)
    | Node(left, v, rootkey, right) ->
        if k >= rootkey then 
            Node(left, v, rootkey, insert right k v)
        else
            Node(insert left k v, v, rootkey, right)

let rec findmin (t : 'a bst) : 'a * key =
    match t with
    | Leaf -> failwith "empty tree"
    | Node (Leaf, v, k, _) -> (v, k)
    | Node (left, _, _, _) -> findmin left

let rec deleteroot (t : 'a bst) (k : key) =
    match t with
    | Leaf -> failwith "empty tree"
    | Node(left, _, _, Leaf) -> left
    | Node(Leaf, _, _, right) -> right
    | Node(left, _, _, right) ->
        
let rec delete (t : 'a bst) (k : key)  =
    match t with
    | Leaf -> Printf.eprintf "key %i not found" k
    | Node(left, v, rootkey, right) ->
        if rootkey = k then 
            v
        else if k > rootkey 
            then find right k
        else
            find left k