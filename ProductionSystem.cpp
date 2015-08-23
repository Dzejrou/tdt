#include "ProductionSystem.hpp"

ProductionSystem::ProductionSystem(EntitySystem& ents, GridSystem& grid)
	: entities_{ents}, grid_{grid}
{ /* DUMMY BODY */ }

void ProductionSystem::update(Ogre::Real delta)
{
	for(auto& ent : entities_.get_component_container<ProductionComponent>())
	{
		if(ent.second.curr_produced >= ent.second.max_produced)
			continue;

		if(ent.second.curr_cd < ent.second.cooldown)
			ent.second.curr_cd += delta;
		else
		{
			spawn_entity(ent.first, ent.second.product_blueprint);
			++ent.second.curr_produced;
			ent.second.curr_cd = 0;
		}
	}
}

void ProductionSystem::spawn_entity(std::size_t producer, const std::string& blueprint)
{
	std::size_t id = entities_.create_entity(blueprint);
	auto& prod_comp = entities_.add_component<ProductComponent>(id);
	prod_comp.producer = producer;

	auto struct_comp = entities_.get_component<StructureComponent>(producer);
	auto phys_comp = entities_.get_component<PhysicsComponent>(producer);
	auto product_phys_comp = entities_.get_component<PhysicsComponent>(id);
	auto product_graph_comp = entities_.get_component<GraphicsComponent>(id);
	if(struct_comp && phys_comp && product_phys_comp && !struct_comp->walk_through)
	{
		std::size_t center_x, center_y;
		std::tie(center_x, center_y) = grid_.get_board_coords(
			grid_.get_node_from_position(
				phys_comp->position.x,
				phys_comp->position.z
		));

		std::size_t top_left_node = grid_.get_node(center_x - struct_comp->radius,
												   center_y - struct_comp->radius);
		std::size_t free_node = Component::NO_ENTITY;
		for(std::size_t i = 0; i < struct_comp->radius + 1; ++i)
		{
			/**
			 * This checks all edges of the building to find a free spot for
			 * the entity to spawn on.
			 */
			auto node = grid_.get_node(center_x - struct_comp->radius + i,
									   center_y - struct_comp->radius - 1);
			if(node != Component::NO_ENTITY && grid_.is_free(node)) // Top row.
			{
				free_node = node;
				break;
			}
			node = grid_.get_node(center_x - struct_comp->radius - 1,
								  center_y - struct_comp->radius + i);
			if(node != Component::NO_ENTITY && grid_.is_free(node)) // Left row.
			{
				free_node = node;
				break;
			}
			node = grid_.get_node(center_x - struct_comp->radius + i,
								  center_y + struct_comp->radius + 1);
			if(node != Component::NO_ENTITY && grid_.is_free(node)) // Botttom row.
			{
				free_node = node;
				break;
			}
			node = grid_.get_node(center_x + struct_comp->radius + 1,
								  center_y - struct_comp->radius + i);
			if(grid_.is_free(node)) // Right row.
			{
				free_node = node;
				break;
			}
		}

		if(free_node != Component::NO_ENTITY)
		{
			auto spawn_node_phys_comp = entities_.get_component<PhysicsComponent>(free_node);
			if(spawn_node_phys_comp)
			{
				product_phys_comp->position.x = spawn_node_phys_comp->position.x;
				product_phys_comp->position.z = spawn_node_phys_comp->position.z;
			}
		}
		else // New entity cannot be placed because the spawning structure is obstructed.
		{
			entities_.destroy_entity(id);
			return;
		}
	}
	else if(phys_comp && product_phys_comp)
	{
		product_phys_comp->position.x = phys_comp->position.x;
		product_phys_comp->position.z = phys_comp->position.z;
	}
	else
	{
		entities_.destroy_entity(id);
		return;
	}

	if(product_graph_comp && product_graph_comp->node)
		product_graph_comp->node->setPosition(product_phys_comp->position);
}