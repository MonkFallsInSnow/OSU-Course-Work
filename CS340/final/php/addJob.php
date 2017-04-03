<?php
	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	//insert into job table
	if($query = $mysqli->prepare("insert into job (employerID,title,description,pay,rating) values (?,?,?,?,?)"))
	{
		if(!$query->bind_param("issss",$_POST['jobEmployer'],$_POST['jobTitle'],$_POST['jobDesc'],$_POST['jobPay'],$_POST['jobRating']))
		{
			print "Bind failed: "  . $query->errno . " " . $query->error;
		}
		
		if(!$query->execute())
		{
			print "Execute failed: "  . $query->errno . " " . $query->error;
		}
		else
		{
			$jobID = $query->insert_id;
			print "<p>Added " . $query->affected_rows . " rows to job.</p>";
		}
		
		$query->close();
	}
	else
	{
		print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
	}
	
	
	
	//associate a job with a skill or skills
	if (isset($_POST["jobSkills"]))
	{
		//job_skill table insert
		$skills = $_POST["jobSkills"];
		$rowCount = 0;
		foreach($skills as $s)
		{
			if($query = $mysqli->prepare("insert into job_skill (jobID,skillID) values (?,?)"))
			{
				if($query->bind_param("ii",$jobID,$s))
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
					print "Bind failed: " . $mysqli->errno . " " . $mysqli->error;
				}
			}
			else
			{
				print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
			}
		}
		
		print "<p>Added " . $rowCount . " rows to job_skill.</p>";
		print "<p><a href='index.php'>Back to form</a><p>";
		$query->close();
	} 
	else 
	{
	  $skills = null;
	  echo "no skill supplied";
	}
?>