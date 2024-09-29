type ('a, 'b) priority_queue =
  | EmptyQueue
  | Node of 'a * 'b * ('a, 'b) priority_queue * ('a, 'b) priority_queue

let rec merge h1 h2 =
  match h1, h2 with
  | EmptyQueue, _ -> h2
  | _, EmptyQueue -> h1
  | Node (p1, e1, l1, r1), Node (p2, e2, l2, r2) ->
    if p1 <= p2 then
      Node (p1, e1, merge r1 h2, l1)
    else
      Node (p2, e2, merge r2 h1, l2)

let insert priority element pq =
  let new_node = Node (priority, element, EmptyQueue, EmptyQueue) in
  merge pq new_node

let extract_min = function
  | EmptyQueue -> failwith "Priority queue is empty"
  | Node (p, e, left, right) -> (e, merge left right)

let is_empty = function
  | EmptyQueue -> true
  | _ -> false

let () =
  let pq = EmptyQueue in
  let pq = insert 3 "three" pq in
  let pq = insert 1 "one" pq in
  let pq = insert 2 "two" pq in
  let (min_elem, pq) = extract_min pq in
  Printf.printf "Min element: %s\n" min_elem;
  let (min_elem, pq) = extract_min pq in
  Printf.printf "Next min element: %s\n" min_elem;
  Printf.printf "Is queue empty? %b\n" (is_empty pq)
