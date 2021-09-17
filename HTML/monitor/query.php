<?php
header('Content-type: application/json');

$server = "localhost";
$username = "XRD";
$passwd = "27mZFsmWzkiTeGsB";
$conn = new mysqli($server, $username, $passwd, "xrd");

if ($conn->connect_error) {
	die("{\"err\": \"无法连接到数据库, 请联系管理员:pingline@outlook.com. Details:".$conn->connect_error . "\"}");
}

$res = mysqli_query($conn, "SELECT * FROM `guest`;");
//var_dump($res);
$res = mysqli_fetch_all($res);
//var_dump($res);
$json_res = "{\"total\":" . count($res) . ",\"rows\":[";

for ($i=0, $size=count($res); $i<$size; ++$i)
{
	$json_res = $json_res . "{\"id\":".$res[$i][0].", \"pre_score\":".$res[$i][1].", \"pre_details\":\"".$res[$i][2]."\", \"exp_score\":".$res[$i][3].", \"exp_details\":\"".$res[$i][4]."\"},";
}
$json_res = substr($json_res, 0, -1);
$json_res = $json_res."]}";
echo str_replace("\r", "", str_replace("\n", "@", $json_res));
?>
