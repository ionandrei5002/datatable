#ifndef BUILDERS_H
#define BUILDERS_H

#include <memory>

#include "types.h"
#include "values/value.h"
#include "viewers/value.h"
#include "schema.h"
#include "column.h"

std::shared_ptr<Value> PrimitiveValueBuilder(Node& node);
std::shared_ptr<Column> ColumnBuilder(Node& node);
std::shared_ptr<ViewerValue> ViewerValueBuilder(Node& node);

std::shared_ptr<Column> ColumnBuilder(Node& node)
{
    Type::type type = node.getType();
//    bool isNullable = node.isNullable();

    std::vector<std::shared_ptr<Column>> decision_table;
    decision_table.push_back(std::make_shared<TypedColumn<Int8Type>>(TypedColumn<Int8Type>()));
    decision_table.push_back(std::make_shared<TypedColumn<Int16Type>>(TypedColumn<Int16Type>()));
    decision_table.push_back(std::make_shared<TypedColumn<Int32Type>>(TypedColumn<Int32Type>()));
    decision_table.push_back(std::make_shared<TypedColumn<Int64Type>>(TypedColumn<Int64Type>()));
    decision_table.push_back(std::make_shared<TypedColumn<FloatType>>(TypedColumn<FloatType>()));
    decision_table.push_back(std::make_shared<TypedColumn<DoubleType>>(TypedColumn<DoubleType>()));
    decision_table.push_back(std::make_shared<DictionaryTypedColumn<StringType>>(DictionaryTypedColumn<StringType>()));

    return decision_table.at(type);
}

std::shared_ptr<Value> PrimitiveValueBuilder(Node& node)
{
    Type::type type = node.getType();
    bool isNullable = node.isNullable();

    std::vector<std::vector<std::shared_ptr<Value>>> decision_table;
    decision_table.push_back(
                std::vector<std::shared_ptr<Value>>({
                                                        std::make_shared<TypedValue<Int8Type>>(TypedValue<Int8Type>()),
                                                        std::make_shared<NullableTypedValue<Int8Type>>(NullableTypedValue<Int8Type>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<Value>>({
                                                        std::make_shared<TypedValue<Int16Type>>(TypedValue<Int16Type>()),
                                                        std::make_shared<NullableTypedValue<Int16Type>>(NullableTypedValue<Int16Type>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<Value>>({
                                                        std::make_shared<TypedValue<Int32Type>>(TypedValue<Int32Type>()),
                                                        std::make_shared<NullableTypedValue<Int32Type>>(NullableTypedValue<Int32Type>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<Value>>({
                                                        std::make_shared<TypedValue<Int64Type>>(TypedValue<Int64Type>()),
                                                        std::make_shared<NullableTypedValue<Int64Type>>(NullableTypedValue<Int64Type>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<Value>>({
                                                        std::make_shared<TypedValue<FloatType>>(TypedValue<FloatType>()),
                                                        std::make_shared<NullableTypedValue<FloatType>>(NullableTypedValue<FloatType>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<Value>>({
                                                        std::make_shared<TypedValue<DoubleType>>(TypedValue<DoubleType>()),
                                                        std::make_shared<NullableTypedValue<DoubleType>>(NullableTypedValue<DoubleType>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<Value>>({
                                                        std::make_shared<TypedValue<StringType>>(TypedValue<StringType>()),
                                                        std::make_shared<NullableTypedValue<StringType>>(NullableTypedValue<StringType>())
                                                    })
                );

    return decision_table.at(type).at(isNullable);
}

std::shared_ptr<ViewerValue> ViewerValueBuilder(Node& node)
{
    Type::type type = node.getType();
    bool isNullable = node.isNullable();

    std::vector<std::vector<std::shared_ptr<ViewerValue>>> decision_table;
    decision_table.push_back(
                std::vector<std::shared_ptr<ViewerValue>>({
                                                        std::make_shared<TypedViewerValue<Int8Type>>(TypedViewerValue<Int8Type>()),
                                                        std::make_shared<NullableTypedViewerValue<Int8Type>>(NullableTypedViewerValue<Int8Type>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<ViewerValue>>({
                                                        std::make_shared<TypedViewerValue<Int16Type>>(TypedViewerValue<Int16Type>()),
                                                        std::make_shared<NullableTypedViewerValue<Int16Type>>(NullableTypedViewerValue<Int16Type>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<ViewerValue>>({
                                                        std::make_shared<TypedViewerValue<Int32Type>>(TypedViewerValue<Int32Type>()),
                                                        std::make_shared<NullableTypedViewerValue<Int32Type>>(NullableTypedViewerValue<Int32Type>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<ViewerValue>>({
                                                        std::make_shared<TypedViewerValue<Int64Type>>(TypedViewerValue<Int64Type>()),
                                                        std::make_shared<NullableTypedViewerValue<Int64Type>>(NullableTypedViewerValue<Int64Type>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<ViewerValue>>({
                                                        std::make_shared<TypedViewerValue<FloatType>>(TypedViewerValue<FloatType>()),
                                                        std::make_shared<NullableTypedViewerValue<FloatType>>(NullableTypedViewerValue<FloatType>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<ViewerValue>>({
                                                        std::make_shared<TypedViewerValue<DoubleType>>(TypedViewerValue<DoubleType>()),
                                                        std::make_shared<NullableTypedViewerValue<DoubleType>>(NullableTypedViewerValue<DoubleType>())
                                                    })
                );
    decision_table.push_back(
                std::vector<std::shared_ptr<ViewerValue>>({
                                                        std::make_shared<TypedViewerValue<StringType>>(TypedViewerValue<StringType>()),
                                                        std::make_shared<NullableTypedViewerValue<StringType>>(NullableTypedViewerValue<StringType>())
                                                    })
                );

    return decision_table.at(type).at(isNullable);
}

#endif // BUILDERS_H
