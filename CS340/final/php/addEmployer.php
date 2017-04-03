<?php
	
	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	if($query = $mysqli->prepare("insert into employer (name,street,city,zip,phone,rating) values (?,?,?,?,?,?)"))
		{
			$optionalVals = array('empStreet','empCity','empZip','empPhone');
			foreach($optionalVals as $val)
			{
				if(empty($_POST[$val]))
				{
					$_POST[$val] = null;
				}
			}
			
			if($query->bind_param("ssssss",$_POST['empName'],$_POST['empStreet'],$_POST['empCity'],$_POST['empZip'],$_POST['empPhone'],$_POST['empRating']))
			{
				if($query->execute())
				{
					print "<p>Added " . $query->affected_rows . " rows to employer.</p>";
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
?>