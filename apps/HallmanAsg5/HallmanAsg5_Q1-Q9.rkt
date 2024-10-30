;; File: HallmanAsg5_Q1-Q9.rkt
;; Author: Jackson Hallman
;; Student Num: 00102945
;; Email: jhallma5@my.athens.edu


;; Problem 1
(define atom1 'apple)
(define atom2 'banana)
(define atom3 'cherry)
(define atom4 'grapes)
(define atom5 'kiwi)

(define list1 `(,atom1))
(define list2 `(,atom2))
(define list3 `(,atom1 ,atom2))
(define list4 `(,atom3 ,atom4))
(define list5 `(,atom2 ,atom3 ,atom4))
(define list6 `(,atom1 ,atom5 ,atom2))
(define list7 `(,atom1 ,atom3 ,atom2 ,atom4))
(define list8 `(,atom5 ,atom1 ,atom4))
(define list9 `(,atom4 ,atom2))
(define list10 `(,atom3 ,atom5))


;; Problem 2
(define list2-1 (cons 'all (cons (cons 'these (cons 'problems '())) '())))
(define list2-2 (cons 'all (cons (cons 'these '()) (cons 'problems '()))))
(define list2-3 (cons (cons 'all (cons 'these '())) (cons 'problems '())))
(define list2-4 (cons (cons 'all (cons 'these (cons 'problems '()))) '()))


;; Problem 3
(define french-fries (car (cons 'french '(fries)))) ;; Result: 'french


;; Problem 4
;; There is no list that makes (null? (cons a l)) true because cons always creates a non-empty list.


;; Problem 5
(define prob5-1 (atom? (car '((meatballs) and spaghetti)))) ;; Result: #f
(define prob5-2 (null? (cdr '((meatballs))))) ;; Result: #t
(define prob5-3 (eq? (car '(two meatballs)) (car (cdr '(two meatballs))))) ;; Result: #f


;; Problem 6
(define (custom-member? a l)
  (if (null? l)
      nil
      (or (eq? (car l) a) (member? a (cdr l)))))


;; Problem 7
(define (nonlat? lst)
  (cond
    ((null? lst) #t)
    ((atom? (car lst)) #f)
    (else (nonlat? (cdr lst)))))


;; Problem 8
(define (member-twice? a lst)
  (define (count a lst)
    (cond
      ((null? lst) 0)
      ((eq? a (car lst)) (+ 1 (count a (cdr lst))))
      (else (count a (cdr lst)))))
  (> (count a lst) 1))


;; Problem 9
(define (seconds lats)
  (map (lambda (lat) (cadr lat)) lats))

;; Testing for problem 9
(define test-lats '((apple banana cherry)
                    (dog cat mouse)
                    (one two three)))
(define result-seconds (seconds test-lats)) ;; Expected result: '(banana cat two)
