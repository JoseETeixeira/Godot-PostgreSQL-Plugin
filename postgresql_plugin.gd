@tool
extends EditorPlugin

var postgresql_manager = null

func _enter_tree():
	postgresql_manager = preload("res://addons/postgresql_plugin/postgresql_manager.gd").new()
	add_control_to_container(CONTAINER_SPATIAL_EDITOR_MENU, postgresql_manager)
	add_tool_menu_item("PostgreSQL Manager", self, "_on_postgresql_manager_button_pressed")

func _exit_tree():
	remove_control_from_container(CONTAINER_SPATIAL_EDITOR_MENU, postgresql_manager)
	remove_tool_menu_item("PostgreSQL Manager")

func _on_postgresql_manager_button_pressed():
	# Add logic to handle what happens when the button is pressed, e.g., open a UI
	print("PostgreSQL Manager button pressed")
