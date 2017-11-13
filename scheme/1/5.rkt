#lang scheme
(define (cc amount kind-of-coins)
  (cond ((= amount 0)  1)
        ((or (< amount 0) (= kind-of-coins 0)) 0)
        (else (+ (cc amount (- kind-of-coins 1))
                 (cc (- amount (correspond kind-of-coins)) kind-of-coins)))))

  (define (correspond kind-of-coins)
    (cond ((= kind-of-coins 1) 50)
          ((= kind-of-coins 2) 5)
          ((= kind-of-coins 3) 10)
          ((= kind-of-coins 4) 25)
          ((= kind-of-coins 5) 1)))
 

(cc 100 5)