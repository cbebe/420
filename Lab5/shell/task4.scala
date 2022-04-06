/** task4.txt
  * Return a key-value pair RDD named “result” containing BOTH all the
  * original one-hop links and all the two-hop links, in which each key stores the source
  * node of a link and the corresponding value stores the destination node of the link.
  *
  * Finding the two-hop links was done by taking the cartesian product of the original pairs
  * with itself, then filter it by a condition that finds the (node, destination) pairs of the
  * destination of the original node. Then, the two-hop links are unioned with the one-hop links
  * to get the final result.
  */
val pairs = sc.textFile("data_input").flatMap { line =>
    val pair = line.split("\t").map(n => n.toInt)
    Map(pair(0) -> pair(1))
}
val cartesian = pairs.cartesian(pairs)
val twoHop = cartesian.filter {
    case ((n1, d1), (n2, d2)) => ((d1 == n1) || (n1 != n2)) && (d1 == n2)
}.map {
    case ((n1, d1), (n2, d2)) => (n1, d2)
}
val result = pairs ++ twoHop
