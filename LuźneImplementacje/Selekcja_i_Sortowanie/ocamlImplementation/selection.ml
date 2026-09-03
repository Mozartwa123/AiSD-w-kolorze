open List
open Printf

(* Prezentacja algorytmu quicksort i magicznych piątek 
Uruchomienie: ocamlc selection.ml, a potem ./a.out *)
let rec printList (s : int list) : unit = 
    match s with
    | [] -> ()
    | a :: rest -> printf "%i " a; printList rest

let partitionStep (s : int list) (pivot : int) : int list * int list * int = 
    fold_left (
        fun (lists : int list * int list * int) element ->
            match lists with
            | (s1, s2, p) ->
                if (element < pivot) then
                    (element :: s1, s2, p)
                else if (element > pivot) then
                    (s1, element :: s2, p)
                else
                    if p == 1 then
                        (element :: s1, s2, 0)
                    else
                        (s1, element :: s2, 1)

    ) ([], [], 0) s


let xs = [5; 4; 2; 7; 1; 8; 42; 51; 45; 48; 11; 23; 351; 24; 35; 12; 27; 20; 43; 256; 302]

let rec quicksort xs =
    match xs with
    | [] -> []
    | a :: [] -> [a]
    | _ -> let (s1, s2, _) = partitionStep xs (hd xs) in
    (* printList s1; printf "\n"; printList s2; *)
    concat [(quicksort s1); (quicksort s2)]
;;

let rec fives (xs : int list) (xss : int list list) : int list list =
    match xs with
    | [] -> xss
    | a :: b :: c :: d :: e :: rest -> (fives rest ([a; b; c; d; e] :: xss))
    | _ -> xs :: xss

let rec findFiveMedian (xss : int list list) : int list = 
    fold_left (
        fun (acc : int list) (xs : int list) -> nth (quicksort xs) ((length xs) / 2) :: acc
        (* printf "sorted (%i): " ((length xs) / 2); printList (quicksort xs); printf "\n"; *)
    ) [] xss

let rec select xs k =
    let n = length xs in
    if n <= k then 
        let _ = fprintf stderr "Size of list (%i) smaller than k (%i)" n k in 42
    else
        if n < 6 then nth (quicksort xs) k else
            let fs = findFiveMedian (fives xs []) in
            let pivot = select fs (length fs / 2)
        in
        let (s1, s2, _) = partitionStep xs pivot in
        let p = length s1 in
        if k = p then pivot else
            if k < p then
                select s1 k
            else select s2 (k - p)

let ys = quicksort xs;;
printList xs;;
printf "\n";;
printList ys;;
printf "\n";;

let n = length xs;;

(* !!! IMPERIALISTYCZNA ŚWINIA !!! *)
for i = 0 to n - 1 do
  printf "%i. %i\n" i (select xs i) 
done