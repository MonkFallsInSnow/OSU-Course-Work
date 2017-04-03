<?php
	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	//if update button clicked
	if(isset($_POST['updateBtn']))
	{
		$stmt = "update job set 
				employerID = ?, 
				title = ?,
				description = ?,
				pay = ?,
				rating = ?
				where id = ?";
				
		if($query = $mysqli->prepare($stmt))
		{
			if($query->bind_param("ssssss",$_POST['empName'],$_POST['title'],$_POST['desc'],$_POST['pay'],$_POST['rating'],$_POST['jobID']))
			{
				if($query->execute())
				{
					print "<p>Updated " . $query->affected_rows . " rows in job.</p>";
					print "<p><a href='index.php'>Back to form</a><p>";
				
				}
				else
				{
					print "Execute failed: "  . $query->errno . " " . $query->error;
				}
			}
			else
			{
				print "Bind failed: "  . $query->errno . " " . $query->error;
			}

			$query->close();
		}
		else
		{
			print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
		}
	}
	
	//if delete button clicked
	if(isset($_POST['deleteBtn']))
	{
		$stmt = "delete from job 
				where id = ?";
				
		if($query = $mysqli->prepare($stmt))
		{
			if($query->bind_param("s",$_POST['jobID']))
			{
				if($query->execute())
				{
					print "<p>Deleted " . $query->affected_rows . " rows from job.</p>";
					print "<p><a href='index.php'>Back to form</a><p>";
				
				}
				else
				{
					print "Execute failed: "  . $query->errno . " " . $query->error;
				}
			}
			else
			{
				print "Bind failed: "  . $query->errno . " " . $query->error;
			}

			$query->close();
		}
		else
		{
			print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
		}
	}
?>