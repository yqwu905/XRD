<?php
$server = "localhost";
$username = "XRD";
$passwd = "27mZFsmWzkiTeGsB";
$conn = new mysqli($server, $username, $passwd, "xrd");
if ($conn->connect_error)
{
	die("无法连接到数据库, 请联系管理员:pingline@outlook.com. Details:" . $conn->connect_error);
}

?>
