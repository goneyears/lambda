#lang racket
(define (list-ref lst n)
  (if (= n 0)
      (car lst)
      (list-ref (cdr lst) (- n 1))))
      
(define (length lst)
  (if (null? lst)
      0
      (+ 1 (length (cdr lst)))))
(define lst1 (list 1 2 3 4))
(length lst1)
(list-ref lst1 2)
