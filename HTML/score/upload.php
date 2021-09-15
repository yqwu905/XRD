<?php
if ($_GET["key"]=="dD999QlNCTA1yBq6")
{
	if ($_GET['type'] != 'guest' || $_GET['id']==null || $_GET['score']==null || $_GET['details']==null) {
		die("非法的请求!");
	}

	$server = "localhost";
	$username = "XRD";
	$passwd = "27mZFsmWzkiTeGsB";
	$conn = new mysqli($server, $username, $passwd, "xrd");
	if ($conn->connect_error) {
		die("无法连接到数据库, 请联系管理员:pingline@outlook.com. Details:" . $conn->connect_error);
	}

	$res = mysqli_query($conn, "UPDATE `xrd`.`guest` SET `exp_score` = '".$_GET['score']."', `exp_details` = '".$_GET['details']."' WHERE `guest`.`id` = ".$_GET["id"].";");
	var_dump($res);
	echo $conn->error;
	echo "done";

} else {
echo "Error key!";
}
 ?>
