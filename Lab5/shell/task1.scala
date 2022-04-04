/** task1.txt
  *
  * Return a variable named “result” storing the maximum indegree among all the
  * nodes.
  *
  * This is found by counting the number of occurrences of a number as a
  * destination node, i.e. as the second element in a line
  */
val result = sc.textFile("data_input").map { line =>
    line.split("\t")(1).toInt
}.groupBy(identity).mapValues(_.size).reduce((acc, value) => {
    if (acc._2 < value._2) value else acc
})._2
