default_task_handler = {
	handle_task = function(id, task)
		task_type = game.get_task_type(task)
		if task_type == game.enum.task.go then
		   res = game.pathfind(id, game.get_task_target)
		   return true
	   	end
	end,

	task_complete = function(id, task)
	end
}
