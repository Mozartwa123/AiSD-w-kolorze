type key = int
type 'a bst = Leaf | Node of 'a bst * 'a * key * 'a bst

let rec find (t : 'a bst) (k : key) : 'a bst =
    (* Zwraca poddrzewo o korzeniu o danym kluczu *)
    match t with
    | Leaf -> Leaf
    | Node(l, v, rk, r) ->
        if k == rk 
            then t
        else if k > rk
            then find r k
        else find l k

let rec insert (t : 'a bst) (k : key) (v : 'a) : 'a bst =
    match t with
    | Leaf -> Node(Leaf, v, k, Leaf)
    | Node(l, vk, rk, r) as n ->
        if k == rk 
            then n
        else if k > rk
            then Node(l, vk, rk, insert r k v)
        else Node(insert l k v, vk, rk, r)

let rec findmin (t : 'a bst) : 'a bst =
    (* zwraca poddrzewo zakorzenione w wierzchołku o najmniejszym kluczu *)
    match t with
    | Leaf -> Leaf
    | Node(Leaf, k, _, _) as n -> n
    | Node(l, k, _, _) -> findmin l

let rec delete (t : 'a bst) (k : key) : 'a bst =
    match t with 
    | Leaf -> Leaf
    | Node(l, v, rk, r) ->
        if k > rk
            then Node(l, v, rk, delete r k)
        else if k < rk
            then Node(delete l k, v, rk, r)
        else(
            match r with
            | Leaf -> l
            | _ -> (match l with
                | Leaf -> r
                | _ -> (
                    match findmin r with
                    | Leaf -> failwith "xd"
                    | Node(_, v, rk, _) -> 
                        Node(l, v, rk, delete r rk)
                    )
                )
            )

let leftRotate (t : 'a bst) : 'a bst =
    match t with
    | Node(Node(t1, v, k, t2), v', k', t3) -> Node(t1, v, k, Node(t2, v', k', t3))
    | _ -> failwith "left rotation of wrong tree"

let rightRotate (t : 'a bst) : 'a bst =
    match t with
    | Node(t1, v, k, Node(t2, v', k', t3)) -> Node(Node(t1, v, k, t2), v', k', t3)
    | _ -> failwith "right rotation of wrong tree"