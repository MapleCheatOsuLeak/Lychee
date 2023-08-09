#pragma once

#include <vector>

#include "../Drawable.h"

/**
 * \brief A drawable which can have children added to it.
 * Transformations applied to a container are also applied to its children.
 */
class Container : public Drawable
{
    std::shared_ptr<DependencyContainer> m_dependencyContainer;
    std::vector<std::shared_ptr<Drawable>> m_children;

protected:
    void LateLoad(const std::shared_ptr<DependencyContainer>& dependencyContainer) override;

public:
    bool PassThroughInput = true;
    /**
     * \brief Controls which axes are automatically sized to this Container's maximum children size.
     * Any sizing manipulations with the Axes of AutoSizeAxes will either be discarded or cause an exception.
     */
    Axes AutoSizeAxes = Axes::None;

    void UpdateClock(double deltaTime) override;
    void Update(bool handleInput) override;
    void Draw() override;

    /**
     * \brief Assigns a new children list to this container.
     * Calling this method will delete all existing children of this container.
     * \param children_vec A list of drawables.
     */
    void SetChildren(const std::vector<std::shared_ptr<Drawable>>& children);
    /**
     * \brief Adds a new child to this container.
     * \param drawable Drawable to be added.
     */
    void Add(const std::shared_ptr<Drawable>& drawable);
};