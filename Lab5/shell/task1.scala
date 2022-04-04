/** task1.txt
  *
  * Return a variable named “result” storing the maximum indegree among all the
  * nodes.
  *
  * This is found by counting the number of occurrences of a number as a
  * destination node, i.e. as the second element in a line
  */
import scala.io.Source
val result = Source.fromFile("data_input").getLines.map {
    line => line.split("\t")(1).toInt
}.toList.groupBy(identity).mapValues(_.size).maxBy(_._2)._2

// Alternative solution using RDD
/*
val result = sc.textFile("data_input").map { line =>
    line.split("\t")(1).toInt
}.groupBy(identity).mapValues(_.size).reduce((acc, value) => {
    if (acc._2 < value._2) value else acc
})._2
*/