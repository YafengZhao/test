
object HelloScala {

  val func = (x: Int) => x * 10

  def m1(f: Int => Int) : Int = {

    f(3)
  }

  def main(args: Array[String]) {

    val r = m1(func)

    println(r)

    val arr = Array(1, 2, 3, 4, 5, 6)

    val r1 = arr.map(x => x * 5)
    val r2 = arr.map(x => x - 1)

    println(r1.toBuffer)
    println(r2.toBuffer)
    println(arr.toBuffer)
  }
}
