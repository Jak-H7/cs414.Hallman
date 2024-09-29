type 'a stack =
  | EmptyStack
  | StackNode of 'a * 'a stack

let push x s = StackNode (x, s)

let pop = function
  | EmptyStack -> failwith "Stack is empty"
  | StackNode (_, rest) -> rest

let top = function
  | EmptyStack -> failwith "Stack is empty"
  | StackNode (x, _) -> x

let is_empty = function
  | EmptyStack -> true
  | StackNode _ -> false

let () =
  let my_stack = EmptyStack in
  let my_stack = push 10 my_stack in
  let my_stack = push 20 my_stack in
  let my_stack = push 30 my_stack in

  Printf.printf "Top of the stack: %d\n" (top my_stack);
  let my_stack = pop my_stack in
  Printf.printf "Top after pop: %d\n" (top my_stack);
  if is_empty my_stack then
    Printf.printf "Stack is empty\n"
  else
    Printf.printf "Stack is not empty\n"
