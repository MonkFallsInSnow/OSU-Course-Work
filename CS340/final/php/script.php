<?php
	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	
	function showRatings()
	{
		for($i = 1; $i <= 10; $i++)
		{
			print "<option>" . $i . "</option>\n";
		}
	}
	
	function showProficiencies()
	{
		$arr = array(
		0 => 'very poor',
		1 => 'poor',
		2 => 'acceptable',
		3 => 'good',
		4 => 'very good',
		5 => 'excellent',
		);
		
		for($i = 0; $i < count($arr); $i++)
		{
			print "<option>" . $arr[$i] . "</option>\n";
		}
	}

	function selectName($tbl)
	{
		global $mysqli;
		
		if($query = $mysqli->prepare("select id, name from `$tbl`"))
		{
			if(!$query->execute())
			{
				print "Execute failed: "  . $query->errno . " " . $query->error;
			}
		
			if(!$query->bind_result($id,$name))
			{
				print "Bind failed: "  . $query->errno . " " . $query->error;
			}
			
			while($query->fetch())
			{
				print '<option value=" '. $id . ' "> ' . $name . '</option>\n';
			}
			
			$query->close();
		}
		else
		{
			print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
		}
	}

	
	function buildJobTable()
	{
		global $mysqli;
		$arr = array();
		
		//get available employers
		if($query = $mysqli->prepare("select id,name from employer"))
		{
			if(!$query->execute())
			{
				print "Execute failed: "  . $query->errno . " " . $query->error;
			}
		
			if(!$query->bind_result($id,$name))
			{
				print "Bind failed: "  . $query->errno . " " . $query->error;
			}
			
			while($query->fetch())
			{
				$arr[$id] = $name;
			}
			
			$query->close();
		}
		else
		{
			print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
		}
	
	
		//build table
		$stmt = "select j.id, j.employerID, e.name, j.title, j.description, j.pay, j.rating 
				from job j
				inner join employer e
				on j.employerID = e.id";
				
		if($query = $mysqli->prepare($stmt))
		{
			if(!$query->execute())
			{
				print "Execute failed: "  . $query->errno . " " . $query->error;
			}
		
			if(!$query->bind_result($id,$empID,$empName,$title,$desc,$pay,$rating))
			{
				print "Bind failed: "  . $query->errno . " " . $query->error;
			}
			
			while($query->fetch())
			{
				print  "<br>
						<form method='post' action='updateJob.php'>
							<table class='table'>
								<tr>
								<td><select name='empName'>";
									foreach($arr as $key => $val)
									{
										if($key == $empID)
										{
											print "<option value='$empID' selected='selected'>'$val'</option>";
										}
										else
										{
											print "<option value='$key'>'$val'</option>";
										}
									}
									
							print "</select></td>
									<td><input type='text' name='title' value='$title'></td>
									<td><input type='text' name='desc' value='$desc'></td>
									<td><input type='number' name='pay' value='$pay'></td>
									<td><input type='number' name='rating' value='$rating' min='1' max='10'></td>
									<td><input type='submit' name='updateBtn' value='Update'></td>
									<td><input type='submit' name='deleteBtn' value='Delete'></td>
									<td><input type='hidden' name='jobID' value='$id'></td>
								</tr>
							</table>
						</form>
						<br>";
			}
			
			$query->close();
		}
		else
		{
			print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
		}
	}
?>