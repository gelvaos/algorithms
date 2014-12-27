(ns quadratic-sort-algos.core
  (:use [clojure.java.io :as io]))


(defn selection-sort [array]
  "Selection sort algorithm implementation"
  (let [a (transient array)
        n (count array)]
    (doseq [idx (range n)]
      (loop [i (+ 1 idx)]
        (when (< i n)
          (let [e-idx (nth a idx)
                e-i (nth a i)]
            (when (< e-i e-idx)
              (assoc! a idx e-i)
              (assoc! a i e-idx)))
          (recur (inc i)))))
    (persistent! a)))


(defn insertion-sort [array]
  "Insertion sort algorithm implementation"
  (let [a (transient array)
        n (count array)]
    (doseq [i (range n)]
      (loop [j i]
        (let [e-j (nth a j)
              e-j-1 (nth a (dec j))]
          (when (and (> j 0) (> e-j-1 e-j)) 
            (assoc! a j e-j-1)
            (assoc! a (dec j) e-j)
            (recur (dec j))))))
    (persistent! a)))


(defn get-num-vector [fname]
  "Get vector of numbers from file"
  (let [v (transient [])]
    (with-open [scanner (Scanner. (File. fname))]
      (while (.hasNextInt scanner)
        (conj! v (.nextInt scanner))))
    (persistent! v)))

(defn run [fname, num-elems, num-execs, sorting-func]
  (let [v (get-num-vector fname)
        exec-times (transient [])]
    (dotimes [_ num-execs]
      (conj! exec-times (time (sorting-func v))))))

(defn -main
  "Main entry point"
  [& args]
  (with-open [wr (writer "result-clojure.dat")]
    (.write wr "#Number-of-elements Selection-Sort-Reverse Selection-Sort-Random Insertion-Sort-Reverse Insertion-Sort-Random")
    (println "Warming up")
    
    (let [num-execs 5]
      
      )))
