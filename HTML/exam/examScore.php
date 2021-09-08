<?php
//header('Content-type: application/json');
$answer = json_decode($_GET["answer"], true);
$correct = array("B", "B", "B", "B", "B", "C", "D", "D", "D", "D");

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
		echo "第" . ($x+1) ."题错误, 正确选项为:" . $correct[$x] . "\n";
	}
}
echo "您已完成预习题, 得分为:".(string)$score."分";
?>
