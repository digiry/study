<?php
	include "../lib/connection.php";
	$conn = mysqlConnect();
	
	$user_id = $_POST['user_id'];
	$user_password = $_POST['user_password'];
	
	$result = mysql_query("select * from user where user_id = '$user_id' and '$user_password'", $conn);
	while ($data = mysql_fetch_array($result)) {
		echo $data[gender];
		session_start();
		$_SESSION['user_id'] = $user_id;
		echo "<script>location.href='/facebook/';</script>"
		exit;
	}
	
	echo "no";
?>