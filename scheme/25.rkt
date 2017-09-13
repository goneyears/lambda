#lang scheme
(define (square x)
  (* x x))

(define (miller-rabin-test n)
  (define (check a n)
    (let ((r (remainder (square a) n)))
      (if (and (> a 1)
               (< a (- n 1))
               (= r 1))
          0
          r)))
  (define (expmod-without-nontrivial-square-root-1 base exp m)
    (cond ((= exp 0) 1)
          ((even? exp)
           (check (expmod-without-nontrivial-square-root-1 base (/ exp 2) m) m))
          (else (remainder (* base (expmod-without-nontrivial-square-root-1 base (- exp 1) m)) m))))
  (define (try-it a)
    (= (expmod-without-nontrivial-square-root-1 a (- n 1) n) 1))
  (try-it (+ 1 (random (- n 1)))))