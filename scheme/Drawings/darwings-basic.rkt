#lang racket
(require graphics/graphics)

;viewport basic operations
(open-graphics)
(define vp (open-viewport "new block window" 500 500))
((draw-pixel vp) (make-posn 1 2))

(define (drawpoint posn)
   (sleep 0.001)
   ((draw-pixel vp) posn))
(define (displays . messages)
  (define (display-iter messagelists)
    (cond ((> (length messagelists) 0)
              (display (car messagelists))
              (newline)
              (display-iter (cdr messagelists)))))
  (display-iter messages)
  )

(define (display-posn posn)
  (display (posn-x posn))
  (display '-)
  (display (posn-y posn))
  (newline))

(define (draw-horizontal start end static)
  (define (draw-horizontal-int start end static)
    (cond ((= start end)
           (drawpoint (make-posn start static)))
          ((< start end)
           (drawpoint (make-posn start static))
           (draw-horizontal-int (+ start 1) end static))
          ((> start end)
           (drawpoint (make-posn start static))
           (draw-horizontal-int (- start 1) end static))))
  (draw-horizontal-int (round start) (round end) (round static)))


(define (draw-vertical start end static)
  (define (draw-vertical-int start end static)
    (cond ((= start end)
           (drawpoint (make-posn static start)))
          ((< start end)
           (drawpoint (make-posn static start))
           (draw-vertical-int (+ start 1) end static))
          ((> start end)
           (drawpoint (make-posn static start))
           (draw-vertical-int (- start 1) end static))))
  (draw-vertical-int (round start) (round end) (round static)))



(define (draw-angle startposn endposn)
  (let ((x1 (posn-x startposn))
        (y1 (posn-y startposn))
        (x2 (posn-x endposn))
        (y2 (posn-y endposn)))
    (draw-horizontal x1 x2 y1)
    (draw-vertical y1 y2 x2)))


(define (drawline startposn endposn)
  (define k
    (if (= (- (posn-x endposn) (posn-x startposn)) 0)
        'inf
        (/ (- (posn-y endposn) (posn-y startposn)) (- (posn-x endposn) (posn-x startposn)))))
  (displayln k)
  (define b
    (if (eq? k 'inf) 'null (- (posn-y endposn) (* k (posn-x endposn)))))
  (displayln b)
  (define (y x) (if (eq? k 'inf) 'null (round (+ (* k x) b))))

  (define (notexceed? startposn endposn)
    (cond ((eq? k 'inf)
           (not (= (posn-y startposn) (posn-y endposn))))
           (else (not (= (posn-x startposn) (posn-x endposn))))))
  
  (define (drawline-iter startposn endposn)
    (let ((s-x (posn-x startposn))
          (s-y (posn-y startposn))
          (e-x (posn-x endposn))
          (e-y (posn-y endposn)))
      (display (notexceed? startposn endposn))
      (cond ((notexceed? startposn endposn)
             (let ((nextposn
                     (if (eq? k 'inf)
                         (make-posn s-x (+ s-y 1))
                         (make-posn (+ s-x 1) (y (+ s-x 1))))))
               (display-posn startposn)
               (display-posn nextposn)
               (draw-angle startposn nextposn)
               (drawline-iter nextposn endposn))
             ))))
  (cond ((or (< (posn-x startposn) (posn-x endposn))
             (and (eq? k 'inf) (< (posn-y startposn) (posn-y endposn))))
         (drawline-iter startposn endposn))
        (else (drawline-iter endposn startposn)))
 )




(drawline (make-posn 100 20) (make-posn 300 101))


  
