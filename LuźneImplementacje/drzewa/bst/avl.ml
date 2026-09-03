open Bst

type 'b avl = (int * 'b) bst

let getBalance (t : 'a avl) = 
  match t with
  | Leaf -> 0
  | Node(_, (bf, _), _, _) -> bf

let rec insert (t : 'b avl) (k : key) (v : 'b) : 'b avl =
  match t with
    | Leaf -> Node(Leaf, (0, v), k, Leaf)
    | Node(l, (tbf, tv), tk, r) ->
        if k == tk 
            then t
        else 
          if k < tk then
            let lbf = getBalance l and l' = insert l k v in 
              if lbf <> 0 then 
                Node(l', (tbf, tv), tk, r) 
              else (
                  match l' with
                  | Leaf -> failwith "xd"
                  | Node(ll', (lbf', lv'), lk', lr') ->
                    if lbf' = 0 then
                      Node(l', (tbf, tv), tk, r)
                    else
                      (* lbf' <> 0 *)
                      if tbf >= 0 then
                        Node(l', (tbf - 1, tv), tk, r)
                      else
                        if lbf = -1 then 
                          Node(ll', (0, lv'), lk', Node(lr', (0, tv), tk, r))
                        else (
                          match lr' with
                            | Leaf -> failwith "xd"
                            | Node(lrl', (lrbf', lrv'), lrk', lrr') ->
                              Node(
                                Node(ll', ((if lrbf' = -1 then 0 else -1), lv'), lk', lrl'),
                                (0, lrv'), lrk',
                                Node(lrr', ((if lrbf' = 1 then 0 else 1), tv), tk, r)
                              )
                        )
                )
          else let rbf = getBalance r and r' = insert r k v in
            if rbf <> 0 then 
              Node(l, (tbf, tv), tk, r') 
            else (
              match r' with
              | Leaf -> failwith "xd"
              | Node(rl', (rbf', rv'), rk', rr') ->
                if tbf <= 0 then
                  Node(l, (tbf + 1, tv), tk, r')
                else 
                  if rbf' = 1 then
                    Node(Node(l, (0, tv), tk, rl'), (0, rv'), rk', rr')
                  else (
                    match rl' with
                    | Leaf -> failwith "xd"
                    | Node(rll', (rlbf', rlv'), rlk', rlr') ->
                      Node(
                        Node(l, ((if rlbf' = -1 then 0 else -1), tv), tk, rll'),
                          (0, rlv'), rlk',
                        Node(rlr', ((if rlbf' = -1 then 0 else -1), rv'), rk', rr')
                      )
                  )

            )



