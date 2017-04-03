<?php
	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	if($query = $mysqli->prepare("insert into venue (name,street,city,zip,phone,description,rating) values (?,?,?,?,?,?,?)"))
		{
			$optionalVals = array('venueStreet','venueCity','venueZip','venuePhone');
			foreach($optionalVals as $val)
			{
				if(empty($_POST[$val]))
				{
					$_POST[$val] = null;
				}
			}
			
			if($query->bind_param("sssssss",$_POST['venueName'],$_POST['venueStreet'],$_POST['venueCity'],$_POST['venueZip'],$_POST['venuePhone'],$_POST['venueDesc'],$_POST['venueRating']))
			{
				if($query->execute())
				{
					print "<p>Added " . $query->affected_rows . " rows to venue.</p>";
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