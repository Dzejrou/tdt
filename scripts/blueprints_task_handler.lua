default_task_handler = {
	handle_task = function(id, task)
		task_type = game.get_task_type(task)
		target = game.get_task_target(task)

		res = false
		if task_type == game.enum.task.none or
		   not game.task_possible(id, task) then
			res = false
		elseif task_type == game.enum.task.go or
		       task_type == game.enum.task.go_near or
		       task_type == game.enum.task.get_in_range then
			res = game.pathfind(id, target)

			if task_type == game.enum.task.go_near then
				game.pop_last_path_node(id)
			end
	   	elseif task_type == game.enum.task.go_kill then
			t1 = game.create_task(target, game.enum.task.get_in_range)
			t2 = game.create_task(target, game.enum.task.kill)

			game.add_priority_task(id, t2)
			game.add_priority_task(id, t1)

			game.cancel_task(task)
			res = false
		elseif task_type == game.enum.task.kill then
			game.set_combat_target(id, target)
			res = true
		elseif task_type == game.enum.task.go_pick_up_gold then
			t1 = game.create_task(target, game.enum.task.go_near)
			t2 = game.create_task(target, game.enum.task.pick_up_gold)

			game.add_priority_task(id, t2)
			game.add_priority_task(id, t1)

			if game.gold_full(id) then
				game.go_deposit_gold(id, true)
			end

			game.cancel_task(task)
			res = false
		elseif task_type == game.enum.task.pick_up_gold then
			game.transfer_all_gold(target, id)
			if game.get_curr_gold(target) > 0 then
				evt = game.create_entity("")
				game.add_component(evt, game.enum.component.event)
				game.set_event_target(evt, target)
				game.set_handler_of_event(evt, id)
				game.set_event_type(evt, game.enum.event.gold_dropped)
			end

			if game.gold_full(id) then
				game.go_deposit_gold(id)
			end

			res = false
		elseif task_type == game.enum.task.go_deposit_gold then
			t1 = game.create_task(target, game.enum.task.go_near)
			t2 = game.create_task(target, game.enum.task.deposit_gold)

			game.add_priority_task(id, t2)
			game.add_priority_task(id, t1)

			game.cancel_task(task)
			res = false
		elseif task_type == game.enum.task.deposit_gold then
			game.transfer_all_gold(id, target)

			if game.get_curr_gold(id) > 0 then
				game.go_deposit_gold(id)
			end

			res = false
	   	end

		return res
	end,

	task_complete = function(id, task)
		task_type = game.get_task_type(task)
		if task_type == game.enum.task.none or
		   not game.task_type_possible(id, task_type) then
			return true
		end

		res = true

		if task_type == game.enum.task.go or
		   task_type == game.enum.task.go_near then
			res = game.path_queue_empty(id)
		elseif task_type == game.enum.task.get_in_range then
			range = game.get_range(id)
			range = range - (range / 10)
			range = range * range

			target = game.get_task_target(task)
			dist = game.get_distance(id, target)
			res = dist < range and game.in_sight(id, target)
			if res then
				game.clear_path(id)
			end
		elseif task_type == game.enum.task.kill then
			res = game.get_combat_target(id) == game.const.no_ent
		end

		return res
	end
}
