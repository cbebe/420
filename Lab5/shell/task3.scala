/** task3.txt
  * Return an RDD named “result” containing the node ID(s) which have the
  * largest outdegree.
  *
  * This was done by counting the outlinks of each node, then grouping the
  * node IDs which have the max number of outlinks, then return all node IDs if more than
  * one node has the same max outdegree.
  */
val nodeIds = sc.textFile("data_input").map { line =>
    line.split("\t")(0).toInt }
val counts = nodeIds.groupBy(identity).mapValues(_.size)
val maxVal = counts.values.max
val maxPairs = counts.filter{case (_, v) => v == maxVal }
val IdsList = maxPairs.collect().map(_._1).toList
val result = sc.parallelize(IdsList)
