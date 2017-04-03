<?php
	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	if($query = $mysqli->prepare("insert into skill (name,description,proficiency) values (?,?,?)"))
	{
		if(!$query->bind_param("sss",$_POST['skillName'],$_POST['skillDesc'],$_POST['skillProf']))
			{
				print "Bind failed: "  . $query->errno . " " . $query->error;
			}
			
			if(!$query->execute())
			{
				print "Execute failed: "  . $query->errno . " " . $query->error;
			}
			else
			{
				print "<p>Added " . $query->affected_rows . " rows to skill.</p>";
				print "<p><a href='index.php'>Back to form</a><p>";
			}
			
			$query->close();
	}
?>