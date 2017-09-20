#lang racket
(require graphics/graphics)

;viewport basic operations
(open-graphics)
(define vp (open-viewport "new block window" 500 500))
((draw-pixel vp) (make-posn 1 2))

(define (drawpoint posn)
   (sleep 0.002)
   ((draw-pixel vp) posn))


(define (drawline startposn endposn)
  (define (notexceed? startposn endposn)
    (<= (posn-x startposn) (posn-x endposn)))
  (define k (/ (- (posn-y endposn) (posn-y startposn)) (- (posn-x endposn) (posn-x startposn))))
  (define b (- (posn-y endposn) (* k (posn-x endposn))))
  (define (y x) (+ (* k x) b))
  (define (drawline-iter startposn endposn)
    (let ((s-x (posn-x startposn))
          (s-y (posn-y startposn))
          (e-x (posn-x endposn))
          (e-y (posn-y endposn)))
      (cond ((notexceed? startposn endposn)
             (drawpoint startposn)
             (let ((nextposn (make-posn (+ s-x 1) (y (+ s-x 1)))))
               (drawline-iter nextposn endposn))
             ))))
  (drawline-iter startposn endposn))


(drawline (make-posn 1 300) (make-posn 300 300))
  