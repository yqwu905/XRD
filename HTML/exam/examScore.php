<?php
//header('Content-type: application/json');
$answer = json_decode($_GET["answer"], true);
$correct = array("B", "B", "B", "B", "B", "C", "D", "D", "D", "D");

$server = "localhost";
$username = "XRD";
$passwd = "27mZFsmWzkiTeGsB";
$conn = new mysqli($server, $username, $passwd, "xrd");
if ($conn->connect_error) {
	die("无法连接到数据库, 请联系管理员:pingline@outlook.com. Details:" . $conn->connect_error);
}

$details = "";
$score = 0;
for ($x=0; $x<10; $x++)
{
	//echo $x . " " . $correct[$x] . "\n";
	//echo $answer[(string)($x+1)."-"]." ".$correct[$x]." ".(string)$x . " " . $score . "\n";
	if ($answer[(string)($x+1)."-"] == $correct[$x])
	{
		//echo "+10\n";
		$score=$score + 10;
	}
	else
	{
		//echo "\"第" . ($x+1) ."题错误, 正确选项为:" . $correct[$x];
		$details = $details . "第" . ($x+1) . "题错误, 正确的选项为:" . $correct[$x] . "\n";
	}
}
if ($_COOKIE["type"]=="guest")
{
	mysqli_query($conn, "UPDATE `xrd`.`guest` SET `pre_score` = '".$score."', `pre_details` = '".$details."' WHERE `guest`.`id` = ".$_COOKIE["id"].";");
}
//echo $_COOKIE["type"];
//echo $details;
echo "最终成绩为:".$score."分";
$conn->close();
?>
