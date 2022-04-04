/** task2.txt
  *
  * Return a key-value pair RDD named “result” with the keys being the node IDs,
  * and the corresponding value of each key (node) storing a list of all its
  * neighbors.
  *
  * This is done by creating a two-way map of tuples to represent each node's
  * neighbours and then grouping the distinct values by their key
  */
val result = sc.textFile("data_input").flatMap { line =>
    val pair = line.split("\t").map(n => n.toInt)
    Map(pair(0) -> pair(1), pair(1) -> pair(0))
}.groupBy(_._1).mapValues{ buf =>
    buf.map(x => x._2).toList.distinct
}
