type ('a, 'b) tree =
  | Empty
  | Node of 'a list * ('a, 'b) tree list

let rec insert key tree =
  match tree with
  | Empty -> Node ([key], [Empty; Empty])
  | Node (keys, children) ->
      let rec insert_in_list key keys children =
        match keys, children with
        | [], [c] -> [key], [insert key c]
        | k::ks, c::cs ->
            if key < k then
              let new_subtree = insert key c in
              (key::k::ks, new_subtree::cs)
            else
              let ks', cs' = insert_in_list key ks cs in
              (k::ks', c::cs')
      in
      let new_keys, new_children = insert_in_list key keys children in
      Node (new_keys, new_children)

let rec print_tree indent = function
  | Empty -> Printf.printf "%sEmpty\n" indent
  | Node (keys, children) ->
      Printf.printf "%sNode: keys = [%s]\n" indent (String.concat "; " (List.map string_of_int keys));
      List.iter (print_tree (indent ^ "  ")) children

let () =
  let my_tree = Empty in
  let my_tree = insert 10 my_tree in
  let my_tree = insert 5 my_tree in
  let my_tree = insert 15 my_tree in
  let my_tree = insert 8 my_tree in
  let my_tree = insert 20 my_tree in
  print_tree "" my_tree