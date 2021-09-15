<!DOCTYPE html>
<html>
	<head>
		<style>
		body
		{
			background-color: #eef8ff;
		}
		
		h2
		{
			font-family: arial, sans-serif;
			text-align: center;
		}
		
		table
		{
			font-family: arial, sans-serif;
			border-collapse: collapse;
			width: min(100%, 600px);
			margin-left: auto;
			margin-right: auto;
			background-color: #fefefe;
		}
		
		td, th
		{
			border: 2px solid #dddddd;
			text-align: center;
			padding: 8px 4px 8px 4px;
			/*padding: 8px 0px 8px 0px;*/
			/*background-color: #eeeeee;*/
		}
		
		.remark
		{
			text-align: left;
		}
		
		tr:nth-child(even)
		{
			background-color: #fff4ee;
		}
		</style>
		<script src="https://common.cnblogs.com/scripts/jquery-2.2.0.min.js"></script>
		<script type="text/javascript" src="https://blog-static.cnblogs.com/files/blogs/605654/blog_word_effect.js"></script>
	</head>
	<body>
<h2>X射线衍射实验--成绩统计表</h2>
<table>
			<colgroup>
				<col span="1" style="width: 20%;">
				<col span="1" style="width: 20%;">
				<col span="1" style="width: 60%;">
			</colgroup>
			<tr style="background-color: #eeeeee;">
				<th>学生姓名：</th>
				<th>实验成绩：</th>
				<th class="remark">失分细节：</th>
			</tr>
<?php
$file_arr = file("expRecord.json");
for($i=0;$i<count($file_arr);$i++) {
	$json = json_decode($file_arr[$i]);
	echo "<tr><td>".$json->{"id"}."</td>";
	echo "<td>".$json->{"score"}."</td>";
	echo "<td class=\"remark\"><ul>";
	$records = $json->{"record"};
	foreach($records as $record) {
		echo "<li>".$record."</li>";
	}
	echo "</ul></td></tr>";
}
?>
	</table>
	</body>
</html>
</body>
</html>
