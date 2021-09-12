<?php

function guest_new($conn)
{
	mysqli_query($conn, "INSERT INTO `xrd`.`guest` (`id`, `pre_score`, `pre_details`, `exp_score`, `exp_details`) VALUES ('', '-1', '', '-1', '');");
	$res = $conn -> query("SELECT MAX(id) FROM guest");
	$id = mysqli_fetch_array($res);
	return $id[0];
}


//$username = $_GET["username"];
//$passwd = $_GET["passwd"];
$server = "localhost";
$username = "XRD";
$passwd = "27mZFsmWzkiTeGsB";
$conn = new mysqli($server, $username, $passwd, "xrd");
if ($conn->connect_error) {
	die("无法连接到数据库, 请联系管理员:pingline@outlook.com. Details:" . $conn->connect_error);
}

$type = $_GET["type"];
if ($type=="guest")
{
	$id = guest_new($conn);
	echo $id;
}



$conn->close();

?>
