#lang racket
(define (list-ref lst n)
  (cond ((null? lst) '())
        ((= n 0) (car lst))
        (else (list-ref (cdr lst) (- n 1)))))
      
(define (length lst)
  (if (null? lst)
      0
      (+ 1 (length (cdr lst)))))

(define (append list1 list2)
  (if (null? list1)
      list2
      (cons (car list1) (append (cdr list1) list2))))

(define (last lst)
  (list-ref lst (- (length lst) 1)))

(define (pre-list olist n)
  (define (iter lst i)
    (if (= i n) lst
        (iter (append lst (list (list-ref olist i))) (+ i 1))))
  (cond ((= n 0) '())
        (else (iter (list (car olist)) 1))))


(define (reverse lst)
  (if (null? lst)
      lst
      (cons (last lst) (reverse (pre-list lst (- (length lst) 1))))))

(define (even lst)
  (cond ((null? lst) '())
        ((= (length lst) 1) '())          
        (else (cons (cadr lst) (even (cddr lst))))))
(define (odd lst)
  (cond ((null? lst) '())
        ((= (length lst) 1) lst)
        (else (cons (car lst) (odd (cddr lst))))))

  
(define (same-parity-sel lst req)
  (if (null? lst) '()
      (if (req (car lst)) (cons (car lst) (same-parity-sel (cdr lst) req))
          (same-parity-sel (cdr lst) req))))

(define (same-parity lst)
  (if (null? lst) '()
      (let ((re (cond ((odd? (car lst)) odd?)
                      ((even? (car lst)) even?))))
        (cons (car lst) (same-parity-sel (cdr lst) re)))))


(define (scale-list lst factor)
  (if (null? lst) '()
      (cons (* factor (car lst)) (scale-list (cdr lst) factor))))


(define (map proc lst)
  (if (null? lst) '()
      (cons (proc (car lst)) (map proc (cdr lst)))))
(define lst1 (list 1 2 3 4 5))

(define (scale-list-2 lst factor)
  (map (lambda (x) (* x factor)) lst))
(define (ff)
  (display "end"))

(define (for-each proc lst)
  (if (null? lst) (newline)
      (begin (proc (car lst)) (for-each proc (cdr lst)))))
(for-each (lambda (x) (newline) (display x)) lst1)


(define (len lst)
  (if (null? lst) 0
      (+ 1 (len (cdr lst)))))

(define x (list (list 1 2) (list 3 4)))

(define (count-leaves lst)
  (cond ((null? lst) 0)
        ((not (pair? lst)) 1)
        (else (+ (count-leaves (car lst))
                 (count-leaves (cdr lst))))))



;(define lst4 (list 1 (list 2 (list 3 (list 4 (list 5 (list 6  7)))))))
;lst4
;(cdr lst4)
;(define lst40 (cons (car lst4) (cdr lst4)))
;lst40
;(car (cdr (car (cdr (car (cdr (car (cdr (car (cdr (car (cdr lst4))))))))))))
(reverse x)
(define (is-comb-list lst)
  (cond ((null? lst)  #f)
        ((not (pair? lst)) #f)
        ((pair? (car lst)) #t)
        (else (is-comb-list (cdr lst)))))

(define (deep-reverse lst)
  (cond ((null? lst) lst)
        ((not (is-comb-list lst)) (reverse lst))
        (else (cons (deep-reverse (last lst)) (deep-reverse (pre-list lst (- (length lst) 1)))))))
(deep-reverse x)

(deep-reverse (list 3 4))