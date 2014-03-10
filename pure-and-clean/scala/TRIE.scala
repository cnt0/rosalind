var id = 0
def getCurrentId: Int = { id += 1; id }

class Node() {
  val key = getCurrentId
  val children = collection.mutable.Map[Char, Node]()

  override def toString() =
    children.map(z => f"${key} ${z._2.key} ${z._1}\n${z._2.toString()}").mkString
}

val root = new Node()
io.Source.fromFile(new java.io.File(args(0))).getLines()
  .foreach(_.foldLeft(root)(_.children.getOrElseUpdate(_, new Node())))
print(root)