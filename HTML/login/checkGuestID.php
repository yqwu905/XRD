<?php
if ($_GET["id"]==null)
{
	die("非法请求!");
}

$server = "localhost";
$username = "XRD";
$passwd = "27mZFsmWzkiTeGsB";
$conn = new mysqli($server, $username, $passwd, "xrd");
if ($conn->connect_error) {
	die("无法连接到数据库, 请联系管理员:pingline@outlook.com. Details:" . $conn->connect_error);
}
$res = mysqli_query($conn, "SELECT * FROM `xrd`.`guest` where `guest`.`id`=".$_GET["id"].";");
//var_dump($res);
$res = mysqli_fetch_all($res);
if ($res[0]==null)
{
	die("该游客ID不存在!");
}
if ($res[0][3]!=-1)
{
	die("该用户已完成实验,无法重复进行!");
}

?>
