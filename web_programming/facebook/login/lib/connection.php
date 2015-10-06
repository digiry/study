<?php
	function mysqlConnect() {
		$connect = mysql_connect("127.0.0.1", "root", "apmsetup");
		mysql_select_db("facebook", $connect);
		return $connect;
	}
?>