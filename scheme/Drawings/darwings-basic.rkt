#lang racket
(require graphics/graphics)

;viewport basic operations
(open-graphics)
(define vp (open-viewport "new block window" 500 500))

(define (drawpoint posn)
  ; (sleep 0.00001)
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

(define (drawsquare p a)
  ((draw-rectangle vp) (make-posn (- (posn-x p) (/ 0 1)) (- (posn-y p) (/ a 1))) a a))

(define (drawcycle p r)
  ((draw-ellipse vp) (make-posn (- (posn-x p) (/ r 2)) (- (posn-y p) (/ r 2))) r r))

(define (drawsolidcycle p r)
  ((draw-solid-ellipse vp) (make-posn (- (posn-x p) (/ r 2)) (- (posn-y p) (/ r 2))) r r))

(define (drawline startposn endposn)
  (define (draw-line-start) (drawsquare startposn 6))
  (define (draw-line-end) (drawsolidcycle endposn 6))

  (draw-line-start)
  (draw-line-end)
  
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

  (define crease (cond ((eq? k 'inf) (if (<= (posn-y startposn) (posn-y endposn)) 'increase 'decrease))
                         (else (if (<= (posn-x startposn) (posn-x endposn)) 'increase 'decrease))))
  
  (define (drawline-iter startposn endposn)
    (let ((s-x (posn-x startposn))
          (s-y (posn-y startposn))
          (e-x (posn-x endposn))
          (e-y (posn-y endposn)))
      (display (notexceed? startposn endposn))
      (cond ((notexceed? startposn endposn)
             (let ((nextposn
                     (if (eq? k 'inf)
                         (cond ((eq? crease 'increase) (make-posn s-x (+ s-y 1)))
                               ((eq? crease 'decrease) (make-posn s-x (- s-y 1))))
                         (cond ((eq? crease 'increase) (make-posn (+ s-x 1) (y (+ s-x 1))))
                               ((eq? crease 'decrease) (make-posn (- s-x 1) (y (- s-x 1))))))))
               (display-posn startposn)
               (display-posn nextposn)
               (draw-angle startposn nextposn)
               (drawline-iter nextposn endposn))
             ))))
  
  (drawline-iter startposn endposn))

(drawline (make-posn 400 120) (make-posn 350 301))
((draw-string vp) (make-posn 395 100) "ddd")
(drawsquare (make-posn 390 130) 50)
  
(drawsquare (make-posn 330 320) 50)

((get-string-size vp) "k")