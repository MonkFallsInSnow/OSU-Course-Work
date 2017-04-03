<?php
	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	//insert basic activity data
	if($query = $mysqli->prepare("insert into activity (description,rating) values (?,?)"))
	{
		if(!$query->bind_param("ss",$_POST['actDesc'],$_POST['actRating']))
		{
			print "Bind failed: "  . $query->errno . " " . $query->error;
		}
		
		if(!$query->execute())
		{
			print "Execute failed: "  . $query->errno . " " . $query->error;
		}
		else
		{
			$actID = $query->insert_id;
			print "<p>Added " . $query->affected_rows . " rows to activity.</p>";
		}
		
		$query->close();
	}
		
	//associate a skill or skills with an activity
	if (isset($_POST["actSkills"])) //make sure at least one skill was selected
	{	
		//add each skill to the skill_activity table
		$skills = $_POST["actSkills"];
		$rowCount = 0;
		
		foreach($skills as $s)
		{	
			if($query = $mysqli->prepare("insert into skill_activity (skillID,activityID) values (?,?)"))
			{
				if($query->bind_param("ii",$s,$actID))
				{
					if($query->execute())
					{
						$rowCount += $query->affected_rows;
					}
					else
					{
						print "Execute failed: " . $mysqli->errno . " " . $mysqli->error;
					}
				}
				else
				{
					print "Bind failed: "  . $query->errno . " " . $query->error;
				}
			}
			else
			{
				print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
			}
		
			$query->close();
		}
		
		print "<p>Added " . $rowCount . " rows to skill_activity.</p>";
	}
	
	
	//associate an activity with one or more venues
	if (isset($_POST["actVenues"]))
	{	
		//add each activity to the activity_venue table
		$venues = $_POST["actVenues"];
		$rowCount = 0;
		
		foreach($venues as $v)
		{
			if($query = $mysqli->prepare("insert into activity_venue (activityID,venueID) values (?,?)"))
			{
				if($query->bind_param("ii",$actID,$v))
				{
					if($query->execute())
					{
						$rowCount += $query->affected_rows;
					}
					else
					{
						print "Execute failed: " . $mysqli->errno . " " . $mysqli->error;
					}
				}
				else
				{
					print "Bind failed: "  . $query->errno . " " . $query->error;
				}
			}
			else
			{
				print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
			}
			
			$query->close();
		}
	}

	print "<p>Added " . $rowCount . " rows to activity_venue.</p>";
	print "<p><a href='index.php'>Back to form</a><p>";
		

	
?>