;; name: yehoshua lipsker
;; ID: 204038533
;; group: 04
;; username: lipskey
(define (filter p ls)
  (if (null? ls)ls
      (let
          (
              (hd (car ls))
              (rest (cdr ls))
          )
          (if (p hd) (cons hd (filter p rest)) (filter p rest))
       )
  )
)

(define (get-value-by-key ls v)
  (cond
    ((null? ls) '())
    ((string=? (car (car ls)) v) (cdr (car ls)))
    (else (get-value-by-key (cdr ls) v))
  )
)

(define (ends-with suffix str)
  (define (end-helper suffix-list str-list)
    (cond
      ((null? suffix-list)#t)
      ((null? str-list)#f)
      ((char=? (car suffix-list) (car str-list))
       (end-helper (cdr suffix-list) (cdr str-list)))
      (else #f)
    )
  )
  (end-helper (reverse (string->list suffix))(reverse (string->list str)))
)

(define (mul-of-pairs suffix ls)
  (cond
    ((null? ls) 1)
    ((ends-with suffix (car(car ls))) (* (cdar ls) (mul-of-pairs suffix (cdr ls))))
    (else (* 1 (mul-of-pairs suffix (cdr ls))))
  )
)

(define (merge ls1 ls2)
  (cond
    ((null? ls1) ls2)
    ((null? ls2) ls1)
    (else (append(list (car ls1)(car ls2))(merge (cdr ls1) (cdr ls2))))
  )
)

(define (rotate ls n)
  (define (rotate-once list-origin list-copy)
    (cond
      ((null? list-origin) '())
      ((null? (cdr list-origin)) (append (list (car list-origin)) list-copy))
      (else (rotate-once (cdr list-origin) (append list-copy (list (car list-origin)))))
    )
  )
  (cond
    ((= n 0) ls)
    (else (rotate (rotate-once ls '()) (- n 1)))
  )
)

(define (quicksort comp)
  (define (sortquick inlist)
    (cond
      ((null? inlist) '())
      (else
       (append
        (append
         (append (sortquick (filter (lambda (x) (< (comp x (car inlist)) 0)) (cdr inlist)))
                 (sortquick (filter (lambda (x) (= (comp x (car inlist)) 0)) (cdr inlist)))
         )
         (list (car inlist))
        )
        (sortquick (filter (lambda (x) (> (comp x (car inlist)) 0)) (cdr inlist)))
       )
      )
    )
  )
  (lambda (ls) (sortquick ls)
  )
)

(define (hd sequence)
  (car (sequence))
)

(define (tail sequence)
  (cdr (sequence))
  ;;(cons ((cdr (sequence)) (car (sequence))) cdr (sequence))
)

(define (seq n)
  (lambda () (cons n (seq (+ n 1))))
)

(define (seq-gen n g)
  (lambda () (cons n (seq-gen (g n) g))
  )
)

(define (cyclic-seq ls)
  (lambda ()(cons (car ls) (cyclic-seq (rotate ls (- (length ls) 1)))))
)

(define (make-dictionary)
  (define (dict ls)
    (lambda (x)
      (cond
        ((null? x) ls)
        ((pair? x) (dict (append (filter (lambda (y)(not (string=? (car y)(car x)))) ls) (list x))))
        (else (get-value-by-key ls x))
      )
    )
  )
  (dict '())
)

(load "test.scm")